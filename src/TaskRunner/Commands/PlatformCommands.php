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
        $workingDir = $this->getComposer()->getWorkingDir();
        $source = $workingDir . "/profiles/multisite_drupal_standard/";
        $target = $workingDir . "/vendor/release/multisite_drupal_standard/";
        if (file_exists($source) && file_exists($target . "/.git")) {
          $this->taskComposerInstall()
           ->dir($source)
           ->preferDist()
           ->run();

          $this->taskRsync()
            ->fromPath($source)
            ->toPath($target)
            ->recursive()
            ->excludeVcs()
            ->exclude($source . "/vendor/")
            ->verbose()
            ->progress()
            ->rawArg("-L")
            ->humanReadable()
            ->stats()
            ->run();
        }
    }
}
