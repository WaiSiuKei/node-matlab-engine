#include <nan.h>
#include "engine.h"
#include "matrix.h"

using namespace Nan;
using namespace std;
using namespace v8;

NAN_METHOD(GetVersion) {
	Engine *ep;
	mxArray *T = NULL;
	size_t buflen = 0;
	char *buf = NULL;

	if (!(ep = engOpen(NULL))) {
		info.GetReturnValue().Set(EmptyString());
	}
	engSetVisible(ep, 0);

	engEvalString(ep, NULL);

	engEvalString(ep, "a = gm.Version()");
	
	T = engGetVariable(ep, "a");
	
	buflen = (mxGetM(T) * mxGetN(T)) + 1;

	buf = mxArrayToString(T);

	engClose(ep);

    info.GetReturnValue().Set(New<String>(buf).ToLocalChecked());
}


NAN_MODULE_INIT(Init) {
    Nan::Set(target, New<String>("gm3Version").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(GetVersion)).ToLocalChecked());
}

NODE_MODULE(matlab, Init)