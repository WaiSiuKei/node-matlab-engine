#include <nan.h>
#include <stdlib.h>
#include "engine.h"
#include "matrix.h"

using namespace Nan;
using namespace std;
using namespace v8;

class Work : public Nan::AsyncWorker
{
public:
  Work(Nan::Callback *callback) : AsyncWorker(callback){};
  ~Work(){};
  void Execute();
  void Destory(){};

private:
  string result = "";
  

protected:
  void HandleOKCallback();
  void HandleErrorCallback(){};
};

void Work::Execute()
{
  Engine *ep;
  mxArray *T = NULL;
  size_t buflen = 0;
  char *buf = NULL;

  if (!(ep = engOpen(NULL)))
  {
    return;
  }
  engSetVisible(ep, 0);

  engEvalString(ep, NULL);

  engEvalString(ep, "a = version()");

  T = engGetVariable(ep, "a");

  buflen = (mxGetM(T) * mxGetN(T)) + 1;

  buf = mxArrayToString(T);

  engClose(ep);

  this->result = buf;
}

void Work::HandleOKCallback()
{
  Nan::HandleScope scope;
  Local<Value> argv[] = {Nan::New<String>(this->result).ToLocalChecked()};
  this->callback->Call(1, argv);
}

NAN_METHOD(GetVersion)
{
  Local<Function> cb = Local<Function>::Cast(info[0]);
  Nan::Callback *callback = new Nan::Callback(cb);
  Nan::AsyncQueueWorker(new Work(callback));

  info.GetReturnValue().Set(Nan::Null());
}

NAN_MODULE_INIT(Init)
{
  Nan::Set(target, New<String>("gm3Version").ToLocalChecked(),
           GetFunction(New<FunctionTemplate>(GetVersion)).ToLocalChecked());
}

NODE_MODULE(matlab, Init)