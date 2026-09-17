#include "Core/Net/Rest/RestResponseState.h"

#include "Misc/ScopeLock.h"

namespace Gs2::Core::Net::Rest
{
    bool FRestResponseState::Complete(int32 Code, const FString& Body)
    {
        FScopeLock Lock(&Mutex);
        if (bCompleted)
        {
            return false;
        }
        ResponseCode = Code;
        ResponseBody = Body;
        bCompleted = true;
        return true;
    }

    bool FRestResponseState::IsComplete() const
    {
        FScopeLock Lock(&Mutex);
        return bCompleted;
    }

    bool FRestResponseState::TryGetResponse(int32& OutCode, FString& OutBody) const
    {
        FScopeLock Lock(&Mutex);
        if (!bCompleted)
        {
            return false;
        }
        OutCode = ResponseCode;
        OutBody = ResponseBody;
        return true;
    }
}
