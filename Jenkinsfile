env.RELEASE_NAME = "${env.JOB_NAME}".replaceAll('%2F','-').replaceAll('/','-').trim()
env.slackMessage = "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}>"
slackSend color: "good", message: "${env.slackMessage} started."

try {
    parallel (
        'standard-ec-resp' : {
            // Build and test the standard profile with ec_resp theme
            node('php5') {
                try {
                    withEnv([
                        "BEHAT_PROFILE=standard_ec_resp",
                        "THEME_DEFAULT=ec_resp"
                    ]) {
                        executeStages('standard ec_resp')
                    }
                } catch(err) {
                    throw(err)
                }
            }
        },
        'standard-ec-europa' : {
            // Build and test the standard profile with europa theme
            node('php5') {
                try {
                    withEnv([
                        "THEME_DEFAULT=ec_europa"
                    ]) {
                        executeStages('standard ec_europa')
                    }
                } catch(err) {
                    throw(err)
                }
            }
        },
        'communities-ec-resp' : {
            // Build and test the communities profile with ec_resp theme
            node('php5') {
                try {
                    withEnv([
                        "BEHAT_PROFILE=communities_ec_resp",
                        "PLATFORM_PROFILE=multisite_drupal_communities"
                    ]) {
                        executeStages('communities ec_resp')
                    }
                } catch(err) {
                    throw(err)
                }
            }
        },
        'communities-ec-europa' : {
            // Build and test the communities profile with europa theme
            node('php5') {
                try {
                    withEnv([
                        "BEHAT_PROFILE=communities",
                        "PLATFORM_PROFILE=multisite_drupal_communities",
                        "THEME_DEFAULT=ec_europa"
                    ]) {
                        executeStages('communities ec_europa')
                    }
                } catch(err) {
                    throw(err)
                }
            }
        }
    )
} catch(err) {
    slackSend color: "danger", message: "${env.slackMessage} failed."
    throw(err)
}

slackSend color: "good", message: "${env.slackMessage} complete."

/**
 * Execute profile stages.
 *
 * @param label The text that will be displayed as stage label.
 */
void executeStages(String label) {
    // Use random ports for the HTTP mock and PhantomJS, compute paths, use random DB name
    Random random = new Random()
    env.PROJECT = 'platform-dev'
    tokens = "${env.WORKSPACE}".tokenize('/')
    env.SITE_PATH = tokens[tokens.size()-1]
    env.DB_NAME = "${env.PROJECT}".replaceAll('-','_').trim() + '_' + sh(returnStdout: true, script: 'date | md5sum | head -c 4').trim()
    env.HTTP_MOCK_PORT = random.nextInt(50000) + 10000
    if (env.WD_PORT == '0') {
        env.WD_PORT = env.HTTP_MOCK_PORT.toInteger() + 1
    }
    env.WD_HOST_URL = "http://${env.WD_HOST}:${env.WD_PORT}/wd/hub"

    try {
        stage('Init & Build ' + label) {
            deleteDir()
            checkout scm
            sh 'COMPOSER_CACHE_DIR=/dev/null composer install --no-suggest'
            withCredentials([
                [$class: 'UsernamePasswordMultiBinding', credentialsId: 'mysql', usernameVariable: 'DB_USER', passwordVariable: 'DB_PASS'],
                [$class: 'UsernamePasswordMultiBinding', credentialsId: 'flickr', usernameVariable: 'FLICKR_KEY', passwordVariable: 'FLICKR_SECRET']
            ]) {
                sh "./bin/phing build-platform-dev -Dcomposer.bin=`which composer` -D'behat.base_url'='$BASE_URL/$SITE_PATH/build' -D'behat.wd_host.url'='$WD_HOST_URL' -D'behat.browser.name'='$WD_BROWSER_NAME' -D'env.FLICKR_KEY'='$FLICKR_KEY' -D'env.FLICKR_SECRET'='$FLICKR_SECRET' -D'integration.server.port'='$HTTP_MOCK_PORT' -D'varnish.server.port'='$HTTP_MOCK_PORT' -D'platform.profile.name'='$PLATFORM_PROFILE' -D'platform.site.theme_default'='$THEME_DEFAULT'"
                sh "./bin/phing install-platform -D'drupal.db.name'='$DB_NAME' -D'drupal.db.user'='$DB_USER' -D'drupal.db.password'='$DB_PASS' -D'platform.profile.name'='$PLATFORM_PROFILE' -D'platform.site.theme_default'='$THEME_DEFAULT'"
            }
        }

        stage('Check & Test ' + label) {
            sh './bin/phpcs --report=full --report=source --report=summary -s'
            sh './bin/phpunit -c tests/phpunit.xml'
            wrap([$class: 'AnsiColorBuildWrapper', colorMapName: 'xterm']) {
                timeout(time: 2, unit: 'HOURS') {
                    if (env.WD_BROWSER_NAME == 'phantomjs') {
                        sh "phantomjs --webdriver=${env.WD_HOST}:${env.WD_PORT} &"
                    }
                    sh "./bin/behat -c build/behat.yml -p ${env.BEHAT_PROFILE} --colors -f pretty --strict"
                }
            }
        }
    } catch(err) {
        throw(err)
    } finally {
        withCredentials([
            [$class: 'UsernamePasswordMultiBinding', credentialsId: 'mysql', usernameVariable: 'DB_USER', passwordVariable: 'DB_PASS']
        ]) {
            sh 'mysql -u $DB_USER --password=$DB_PASS -e "DROP DATABASE IF EXISTS $DB_NAME;"'
        }
    }
}
