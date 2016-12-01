node('linux') {

    Random random = new Random()
    env.PROJECT = 'platform-dev'
    tokens = "${env.WORKSPACE}".tokenize('/')
    env.SITE_PATH = tokens[tokens.size()-1]
    env.DB_NAME = "${env.PROJECT}".replaceAll('-','_').trim() + '_' + sh(returnStdout: true, script: 'date | md5sum | head -c 4').trim()
    env.RELEASE_NAME = "${env.JOB_NAME}".replaceAll('%2F','-').replaceAll('/','-').trim()
    env.HTTP_MOCK_PORT = random.nextInt(50000) + 10000
    env.WD_PORT = env.HTTP_MOCK_PORT.toInteger() + 1
    env.WD_HOST_URL = "http://${env.WD_HOST}:${env.WD_PORT}/wd/hub"

    stage('Init') {
        deleteDir()
        checkout scm
        setBuildStatus("Build started.", "PENDING");
        slackSend color: "good", message: "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}> started."
    }

    try {
        sh 'composer install --no-suggest'
        stage('Build') {
            withCredentials([
                [$class: 'UsernamePasswordMultiBinding', credentialsId: 'mysql', usernameVariable: 'DB_USER', passwordVariable: 'DB_PASS'],
                [$class: 'UsernamePasswordMultiBinding', credentialsId: 'flickr', usernameVariable: 'FLICKR_KEY', passwordVariable: 'FLICKR_SECRET']
            ]) {
                sh "./bin/phing build-platform-dev -Dcomposer.bin=`which composer` -D'behat.base_url'='$BASE_URL/$SITE_PATH/build' -D'behat.wd_host.url'='$WD_HOST_URL' -D'env.FLICKR_KEY'='$FLICKR_KEY' -D'env.FLICKR_SECRET'='$FLICKR_SECRET' -D'integration.server.port'='$HTTP_MOCK_PORT' -D'varnish.server.port'='$HTTP_MOCK_PORT'"
                sh "./bin/phing install-platform -D'drupal.db.name'='$DB_NAME' -D'drupal.db.user'='$DB_USER' -D'drupal.db.password'='$DB_PASS'"
            }
        }

        stage('Check') {
            sh './bin/phpcs'
        }

        stage('Test') {
            wrap([$class: 'AnsiColorBuildWrapper', colorMapName: 'xterm']) {
                timeout(time: 2, unit: 'HOURS') {
                    sh "phantomjs --webdriver=127.0.0.1:${env.WD_PORT} &"
                    sh './bin/behat -c build/behat.api.yml --colors -f pretty --strict'
                    sh './bin/behat -c build/behat.i18n.yml --colors -f pretty --strict'
                }
            }
        }

        stage('Package') {
            sh "./bin/phing build-multisite-dist -Dcomposer.bin=`which composer`"
            sh "cd build && tar -czf ${env.RELEASE_PATH}/${env.RELEASE_NAME}.tar.gz ."
            setBuildStatus("Build complete.", "SUCCESS");
            slackSend color: "good", message: "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}> complete."
        }

    } catch(err) {
        setBuildStatus("Build failed.", "FAILURE");
        slackSend color: "danger", message: "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}> failed."
        throw(err)
    } finally {
        withCredentials([
            [$class: 'UsernamePasswordMultiBinding', credentialsId: 'mysql', usernameVariable: 'DB_USER', passwordVariable: 'DB_PASS']
        ]) {
            sh 'mysql -u $DB_USER --password=$DB_PASS -e "DROP DATABASE IF EXISTS $DB_NAME;"'
        }
    }
}

void setBuildStatus(String message, String state) {
    step([
        $class: "GitHubCommitStatusSetter",
        contextSource: [$class: "ManuallyEnteredCommitContextSource", context: "${env.BUILD_CONTEXT}"],
        errorHandlers: [[$class: "ChangingBuildStatusErrorHandler", result: "UNSTABLE"]],
        statusResultSource: [$class: "ConditionalStatusResultSource", results: [[$class: "AnyBuildResult", message: message, state: state]]]
    ]);
}
