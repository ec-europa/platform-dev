<?php

namespace NextEuropa\TaskRunner\Commands;

use EC\OpenEuropa\TaskRunner\Commands\AbstractCommands;
use EC\OpenEuropa\TaskRunner\Contract\ComposerAwareInterface;
use EC\OpenEuropa\TaskRunner\Traits\ComposerAwareTrait;
use Robo\LoadAllTasks;
use Symfony\Component\Console\Input\InputOption;

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
        $branch = "";
        $tag = "";
        $workingDir = $this->getComposer()->getWorkingDir();
        $source = $workingDir . "/profiles/multisite_drupal_standard/";
        $target = $workingDir . "/vendor/release/multisite_drupal_standard/";

        exec('git rev-parse --abbrev-ref HEAD', $sourceBranch);
        $onReleaseBranch = !empty($sourceBranch) ? in_array(strtok($sourceBranch[0], '/'), array("release", "master")) : false;
        $rsyncLocations = file_exists($source) && file_exists($target . "/.git");

        if ($onReleaseBranch && $rsyncLocations) {

          exec('git --git-dir=' . $target . '.git show-ref refs/heads/pre-' . $sourceBranch[0], $targetBranch, $targetBranchExists);
          $this->taskGitStack()->pull()->dir($target)->run();

          if ($targetBranchExists === 1) {
            $this->taskGitStack()->exec('git checkout -b pre-' .  $sourceBranch[0])->dir($target)->run();
            $this->taskGitStack()->exec('git push -u origin pre-' . $sourceBranch[0])->dir($target)->run();
          }
          else {
            $this->taskGitStack()->checkout('pre-' . $sourceBranch[0])->pull()->dir($target)->run();
          }

          $this->taskComposerInstall()
           ->dir($source)
           ->run();

          $this->taskRsync()
            ->fromPath($source)
            ->toPath($target)
            ->recursive()
            ->excludeVcs()
            ->rawArg("-L")
            ->humanReadable()
            ->stats()
            ->run();

         $this->taskGitStack()
           ->add('-A')
           ->commit('Pre release delivery.')
           ->push()
           ->dir($target)
           ->run();
        }
    }
}
