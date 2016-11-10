node('master') {

    // Cleanup foder DB etc.
    stage('Prep') {
        // make sure we clean things before we do anything
        deleteDir()
        checkout scm
    }

    // Build, Install etc. 
    stage('Build') {
        // run composer install
        sh 'composer install --no-suggest'
        // Build
        sh './bin/phing build-platform-dev -Dcomposer.bin=`which composer`'
    }
    
    // Testing stage
    stage('phpcs') {
        // running all phpcs
        sh "./bin/phpcs"
    }
}
