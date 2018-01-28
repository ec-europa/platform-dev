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
        $onReleaseBranch = in_array(strtok($sourceBranch[0], '/'), array("release", "master"));
        $rsyncLocations = file_exists($source) && file_exists($target . "/.git");

        if ($onReleaseBranch && $rsyncLocations) {
          $tag = $this->taskGitStack()->exec('describe --abbrev=0 --tags')->dir($target)->stopOnFail()->run();

          $this->taskGitStack()
            ->stopOnFail()
            ->checkout($sourceBranch[0])
            ->pull()
            ->dir($target)
            ->run();

//          $this->taskComposerInstall()
//           ->dir($source)
//           ->preferDist()
//           ->run();

//          $this->taskRsync()
//            ->fromPath($source)
//            ->toPath($target)
//            ->recursive()
//            ->excludeVcs()
//            ->progress()
//            ->rawArg("-L")
//            ->humanReadable()
//            ->stats()
//            ->run();

//         $this->taskGitStack()
//           ->stopOnFail()
//           ->add('-A')
//           ->commit('First release test.')
//           ->push('origin','master')
//           ->tag('0.0.1')
//           ->push('origin','0.0.1')
//           ->dir($target)
//           ->run();
        }
    }
}
