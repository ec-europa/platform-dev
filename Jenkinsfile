node('master') {

    Random random = new Random()
    env.PROJECT = 'platform-dev'
    tokens = "${env.WORKSPACE}".tokenize('/')
    env.SITE_PATH = tokens[tokens.size()-1]
    env.DB_NAME = "${env.PROJECT}".replaceAll('-','_').trim() + '_' + sh(returnStdout: true, script: 'date | md5sum | head -c 4').trim()
    env.RELEASE_NAME = "${env.JOB_NAME}".replaceAll('%2F','-').replaceAll('/','-').trim()
    env.HTTP_MOCK_PORT = random.nextInt(50000) + 10000

    stage('Init') {
        deleteDir()
        slackSend color: "good", message: "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}> started"
        checkout scm
    }

    try {
        sh 'composer install --no-suggest'
        stage('Build') {
            withCredentials([
                [$class: 'UsernamePasswordMultiBinding', credentialsId: 'mysql', usernameVariable: 'DB_USER', passwordVariable: 'DB_PASS'],
                [$class: 'UsernamePasswordMultiBinding', credentialsId: 'flickr', usernameVariable: 'FLICKR_KEY', passwordVariable: 'FLICKR_SECRET']
            ]) {
                sh "./bin/phing build-platform-dev -Dcomposer.bin=`which composer` -D'behat.base_url'='$BASE_URL/$SITE_PATH/build' -D'env.FLICKR_KEY'='$FLICKR_KEY' -D'env.FLICKR_SECRET'='$FLICKR_SECRET' -D'integration.server.port'='$HTTP_MOCK_PORT' -D'varnish.server.port'='$HTTP_MOCK_PORT'"
                sh "./bin/phing install-platform -D'drupal.db.name'='$DB_NAME' -D'drupal.db.user'='$DB_USER' -D'drupal.db.password'='$DB_PASS'"
            }
        }

        stage('Check') {
            sh './bin/phpcs'
        }

        stage('Test') {
            wrap([$class: 'AnsiColorBuildWrapper', colorMapName: 'xterm']) {
                sh './bin/behat -c build/behat.api.yml --colors -f pretty --strict'
                sh './bin/behat -c build/behat.i18n.yml --colors -f pretty --strict'
            }
        }

        stage('Package') {
            sh "./bin/phing build-multisite-dist -Dcomposer.bin=`which composer`"
            sh "tar -czf ${env.RELEASE_PATH}/${env.RELEASE_NAME}.tar.gz build"
            slackSend color: "good", message: "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}> finished :+1:"
        }

    } catch(err) {
        slackSend color: "warning", message: "<${env.BUILD_URL}|${env.RELEASE_NAME} build ${env.BUILD_NUMBER}> failed :-1:"
        throw(err)
    } finally {
        withCredentials([
            [$class: 'UsernamePasswordMultiBinding', credentialsId: 'mysql', usernameVariable: 'DB_USER', passwordVariable: 'DB_PASS']
        ]) {
            sh 'mysql -u $DB_USER --password=$DB_PASS -e "DROP DATABASE IF EXISTS $DB_NAME;"'
        }
    }
}
