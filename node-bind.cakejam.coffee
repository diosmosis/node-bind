cakejam = require 'cakejam'

node_ext = cakejam.targets.node_ext

exports.test_ext = node_ext 'test_ext', __dirname,
  sources: ['tests/test.cpp']
  includes: ['.']
  cxxoptions: '-std=c++0x'

