/*
 * Copyright (c) 2016, Bojan Šernek <bojan@distopiksound.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <v8.h>
#include <node.h>
#include "nan.h"

#include <sox.h>

using namespace v8;
using namespace node;


namespace nodesox {

    NAN_METHOD(soxbind_get_version) {
        sox_version_info_t const* ver = sox_version_info();
        Local<Array> ret = Nan::New<Array>();

        Nan::Set(ret, 0, Nan::New<String>(ver->version).ToLocalChecked());
        Nan::Set(ret, 1, Nan::New<String>(ver->time).ToLocalChecked());
        Nan::Set(ret, 2, Nan::New<String>(ver->distro).ToLocalChecked());

        info.GetReturnValue().Set(ret);
    }

    void Initialize(Handle<Object> target) {
        Nan::HandleScope scope;

        Nan::SetMethod(target, "soxbind_get_version", soxbind_get_version);
    }
}

NODE_MODULE(bindings, nodesox::Initialize);
