const native    = require('bindings')('bindings'),
      stream    = require('stream'),
      util      = require('util'),
      Transform = stream.Transform

exports.quality = {
  quick:    'quick',
  low:      'low',
  medium:   'medium',
  high:     'high',
  veryHigh: 'veryHigh'
}

exports.phase = {
  linear:       'linear',
  intermediate: 'intermediate',
  minimum:      'minimum',
  steepFilter:  'steepFilter'
}

exports.format = {
  float32: 'float32',
  int16:   'int16',
  int24:   'int24',
  int32:   'int32'
}

exports.channels = {
  interleaved: 'interleaved',
  split:       'split'
}

function Resampler(options) {
  options  = options || {}
  var format   = options.format      || exports.format.int16
  var channels = options.channels    || exports.channels.interleaved
  var quality  = options.quality     || exports.quality.high
  var phase    = options.phase       || exports.phase.linear
  var numCh    = options.numChannels || 1

  this.soxr    = native.soxr_create(format, channels, quality, phase, numCh)
  this.process = function (buf, cb) {
    native.soxr_process(this.soxr, buf, cb)
  }
}

function ResampleStream (options) {
  if (!(this instanceof ResampleStream))
    return new ResampleStream(options)

  Transform.call(this, options)
  this.resampler = new Resampler(options)
}

util.inherits(ResampleStream, Transform)
ResampleStream.prototype._transform = function (chunk, encoding, cb) {
  this.resampler.process(chunk, cb)
}

exports.ResampleStream = ResampleStream
exports.Resampler      = Resampler
