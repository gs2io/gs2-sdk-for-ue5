#include "Core/Net/Rest/RestBinaryResponseState.h"

#include "Misc/ScopeLock.h"

namespace Gs2::Core::Net::Rest
{
    bool FRestBinaryResponseState::Complete(int32 Code, const TArray<uint8>& Body)
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

    bool FRestBinaryResponseState::IsComplete() const
    {
        FScopeLock Lock(&Mutex);
        return bCompleted;
    }

    bool FRestBinaryResponseState::TryGetResponse(int32& OutCode, TArray<uint8>& OutBody) const
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
