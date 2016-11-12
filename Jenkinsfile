node('master') {

    env.PROJECT = 'platform_dev'
    tokens = "${env.WORKSPACE}".tokenize('/')
    env.SITEPATH = tokens[tokens.size()-1]
    env.DBNAME = env.PROJECT + '_' + sh(returnStdout: true, script: 'date | md5sum | head -c 8').trim()

    stage('Init') {
        deleteDir()
        checkout scm
    }

    stage('Build') {
         withCredentials([[
           $class: 'UsernamePasswordMultiBinding',
           credentialsId: 'mysql',
           usernameVariable: 'DBUSER',
           passwordVariable: 'DBPASS']]) {
             sh 'mysql -u $DBUSER --password=$DBPASS -e "CREATE database $DBNAME;"'
             sh 'composer install --no-suggest'
             sh "./bin/phing build-platform-dev -Dcomposer.bin=`which composer` -D'behat.base_url'='$BASE_URL/$SITEPATH/build'"
             sh "./bin/phing install-platform -D'drupal.db.name'='$DBNAME' -D'drupal.db.user'='$DBUSER' -D'drupal.db.password'='$DBPASS'"
        }
    }

    stage('Test') {
        wrap([$class: 'AnsiColorBuildWrapper', colorMapName: 'xterm']) {
          sh './bin/behat -c build/behat.api.yml --colors -f pretty --strict'
          sh './bin/behat -c build/behat.i18n.yml --colors -f pretty --strict'
        }
        sh './bin/phpcs'
    }

    stage('Cleanup') {
        withCredentials([[
           $class: 'UsernamePasswordMultiBinding',
           credentialsId: 'mysql',
           usernameVariable: 'DBUSER',
           passwordVariable: 'DBPASS']]) {
           sh 'mysql -u $DBUSER --password=$DBPASS -e "DROP database $DBNAME;"'
        }
    }
}
