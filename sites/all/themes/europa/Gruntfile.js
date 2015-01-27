'use strict';

module.exports = function (grunt) {

  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    watch: {
      sass: {
        files: ['**/*.{scss,sass}'],
        tasks: ['sass', 'styleguide:dev'],
        options: {
          livereload: true,
        }
      },
    },

    sass: {
      options: {
        sourceMap: true
      },
      dist: {
        files: {
          'css/style-sass.css': 'sass/app.scss'
        },
      }
    },
    styleguide: {
      dev: {
        options: {
          template: {
            src: 'styleguide/template/custom'
          },
          framework: {
            name: 'kss'
          }
        },
        files: {
          'styleguide/assets': 'sass/app.scss'
        }
      }
    },
  });


  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-sass');
  grunt.loadNpmTasks('grunt-styleguide');

  grunt.registerTask('default', ['watch']);

};
