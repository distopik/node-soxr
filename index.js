const {Transform} = require('stream')

class DecoderStream extends Transform {
  transform(chunk, encoding, callback) {
    // 1.) guess which format is at input
    this.emit('format', {
      bits: 16, rate: 44100, endianness: 'little', channels: 2
    })
    // 2.) decode into 64-bit doubles
  }
}

class EncoderStream extends Transform {
  constructor({format = 'wav', bits = 24, rate = 44100, endianess = 'little', floating = false, channels = 2}) {
    this.format = format
    this.bits   = bits
    this.rate   = rate
  }
}

class ResampleStream extends Transform {
  constructor({sourceRate, destRate}) {
    this.sourceRate = sourceRate
    this.destRate   = destRate
  }

  // 64-bit doubles to 64-bit doubles

  transform(chunk, encoding, callback) {
    bindings.proces_resample_chunk(chunk, this.sourceRate, this.destRate, callback)
  }
}

module.exports = {
  EncoderStream, DecoderStream, ResampleStream
}

/// USER CODE -- FROM OUTSIDE THIS MODULE ///

const nodesox = require('node-sox')

const input  = fs.createReadStream('./input.wav'),
      output = fs.createWriteStream('./output.wav')

input
  .pipe(new nodesox.DecoderStream())
  .pipe(new nodesox.ResampleStream({sourceReate: 44100, destRate: 192000}))
  .pipe(new nodesox.EncoderStream({rate: 192000}))
  .pipe(output)
