env.RELEASE_NAME = "${env.JOB_NAME}".replaceAll('%2F','-').replaceAll('/','-').trim()
env.slackMessage = "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}>"
slackSend color: "good", message: "${env.slackMessage} started."

try {
    parallel (
        'standard' : {
            // Build, test and package the standard profile
            node('standard') {
                try {
                    executeStages('standard')
                    stage('Package') {
                        sh "./bin/phing build-multisite-dist -Dcomposer.bin=`which composer`"
                        sh "cd build && tar -czf ${env.RELEASE_PATH}/${env.RELEASE_NAME}.tar.gz ."
                    }
                } catch(err) {
                    throw(err)
                }
            }
        },
        'communities' : {
            // Build and test the communities profile
            node('communities') {
                try {
                    executeStages('communities')
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
                sh "./bin/phing build-platform-dev -Dcomposer.bin=`which composer` -D'behat.base_url'='$BASE_URL/$SITE_PATH/build' -D'behat.wd_host.url'='$WD_HOST_URL' -D'behat.browser.name'='$WD_BROWSER_NAME' -D'env.FLICKR_KEY'='$FLICKR_KEY' -D'env.FLICKR_SECRET'='$FLICKR_SECRET' -D'integration.server.port'='$HTTP_MOCK_PORT' -D'varnish.server.port'='$HTTP_MOCK_PORT' -D'platform.profile.name'='$PLATFORM_PROFILE'"
                sh "./bin/phing install-platform -D'drupal.db.name'='$DB_NAME' -D'drupal.db.user'='$DB_USER' -D'drupal.db.password'='$DB_PASS' -D'platform.profile.name'='$PLATFORM_PROFILE'"
            }
        }

        stage('Check & Test ' + label) {
            sh './bin/phpcs'
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
