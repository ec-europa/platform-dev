<?php

namespace NextEuropa\TaskRunner\Commands;

use EC\OpenEuropa\TaskRunner\Commands\AbstractCommands;
use EC\OpenEuropa\TaskRunner\Contract\ComposerAwareInterface;
use EC\OpenEuropa\TaskRunner\Traits\ComposerAwareTrait;
use Robo\LoadAllTasks;
use Symfony\Component\Console\Input\InputOption;
use JiraRestApi\Issue\IssueService;
use JiraRestApi\Issue\IssueField;
use JiraRestApi\JiraException;

/**
 * Class PlatformCommands
 *
 * @package NextEuropa\TaskRunner\Commands
 */
class PlatformCommands extends AbstractCommands implements ComposerAwareInterface
{
  use ComposerAwareTrait;
  use LoadAllTasks;

  /**
   * Create pull request and ticket.
   *
   * @command platform:request-qa
   *
   * @option token GitHub personal access token, to generate one visit https://github.com/settings/tokens/new
   * @option tag   Upcoming tag you wish to generate a new changelog entry for.
   *
   * @aliases platform:r-qa,pr-qa
   *
   * @param array $options
   *
   */
  public function requestQA(array $options = [
    'token' => InputOption::VALUE_REQUIRED,
    'tag' => InputOption::VALUE_OPTIONAL,
  ])
  {
    $client = new \Github\Client();
    $client->authenticate("verbral", "fa545377782697027275b470aff7fdbbae7b545d", \Github\Client::AUTH_HTTP_PASSWORD);
//    print_r($repo = $client->api('repo')->show("verbruggenalex", "multisite_drupal_standard"));

    $pullRequest = $client->api('pull_request')->create('verbruggenalex', 'multisite_drupal_standard', array(
      'base' => 'release/1.x',
      'head' => 'pre-release/1.x',
      'title' => 'Platform release test',
      'body' => 'This pull request contains a bunch of enhancements and bug-fixes, happily shared with you'
    ));

    var_dump($pullRequest);

    try {
      $issueField = new IssueField();
      $issueField->setProjectKey("MULTISITE")
        ->setSummary($pullRequest['title'] . ": " . $pullRequest['head']['ref'])
        ->setAssigneeName("verbral")
        ->setPriorityName("Critical")
        ->setIssueType("Task")
        ->setDescription("Pull request: " . $pullRequest['html_url']);
      $issueService = new IssueService();
      $ret = $issueService->create($issueField);
      //If success, Returns a link to the created issue .
      var_dump($ret);
      }
    catch (JiraException $e) {
      print("Error Occured! " . $e->getMessage());
    }

    $pullRequest = $client->api('pull_request')
      ->update(
        'verbruggenalex',
        'multisite_drupal_standard',
        $pullRequest['number'],
        array(
          'title' => $ret->key . ': Newtitle.')
      );
  }

  /**
   * Generate releases for profiles provided by platform-dev.
   *
   * @command platform:release
   *
   * @option token GitHub personal access token, to generate one visit https://github.com/settings/tokens/new
   * @option tag   Upcoming tag you wish to generate a new changelog entry for.
   *
   * @aliases platform:r,pr
   *
   * @param array $options
   *
   */
  public function releaseProfiles(array $options = [
    'token' => InputOption::VALUE_REQUIRED,
    'tag' => InputOption::VALUE_OPTIONAL,
  ])
  {
    // Should be made configurable?
    foreach (array("standard", "communities") as $profile) {
      // Set needed variables.
      $workingDir = $this->getComposer()->getWorkingDir();
      $source = $workingDir . "/profiles/multisite_drupal_" . $profile . "/";
      $target = $workingDir . "/vendor/release/multisite_drupal_" . $profile . "/";

      // Set checks.
      exec('git rev-parse --abbrev-ref HEAD', $sourceBranch);
      $onReleaseBranch = !empty($sourceBranch) ? in_array(strtok($sourceBranch[0], '/'), array("release", "master")) : false;
      $rsyncLocations = file_exists($source) && file_exists($target . "/.git");

      // Check if we can create release.
      if ($onReleaseBranch && $rsyncLocations) {

        // Make sure target has latest code available.
        $this->taskGitStack()->pull()->dir($target)->run();

        // Ensure release and pre-release branches are on the remote of target.
        $branches = array($sourceBranch[0], 'pre-' . $sourceBranch[0]);

        // Create branch if needed.
        foreach ($branches as $branch) {
          exec('git --git-dir=' . $target . '.git show-ref refs/heads/' . $branch, $targetBranch, $targetBranchExists);
          if ($targetBranchExists === 1) {
            // Create branch and push tracked remote.
            $this->taskGitStack()
              ->exec('git checkout -b ' . $branch)
              ->exec('git push -u origin ' . $branch)
              ->dir($target)
              ->run();
          }
        }

        // Checkout the pre-release branch since we will not touch the release branch.
        $this->taskGitStack()
          ->checkout($branches[1])
          ->pull()
          ->dir($target)
          ->run();

        // Run composer install.
        $this->taskComposerInstall()
          ->dir($source)
          ->run();

        // Rsync the files to the release location in vendor/release/*
        $this->taskRsync()
          ->fromPath($source)
          ->toPath($target)
          ->recursive()
          ->excludeVcs()
          ->rawArg("-L")
          ->humanReadable()
          ->stats()
          ->run();

        // Commit the synced files to the pre-release branch.
        // @todo: Make message configurable.
        $this->taskGitStack()
          ->add('-A')
          ->commit('Pre release delivery.')
          ->push()
          ->dir($target)
          ->run();
      }
    }
  }
}
