pipeline {
    agent { dockerfile true }
    stages {
        stage('Test') {
            steps {
                echo 'test stage'
                sh 'ls -l'
                sh 'cd bin && chain'
            }
        }
        stage('Build') {
            steps {
                echo 'build stage'
            }
        }
        stage('deploy') {
            steps {
                echo 'deploy stage'
            }
        }
    }
}