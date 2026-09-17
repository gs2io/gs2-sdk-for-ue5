#pragma once

#include "CoreMinimal.h"
#include "HAL/CriticalSection.h"

namespace Gs2::Core::Net::Rest
{
    class GS2CORE_API FRestResponseState
    {
        mutable FCriticalSection Mutex;
        bool bCompleted = false;
        int32 ResponseCode = 999;
        FString ResponseBody;

    public:
        FRestResponseState() = default;
        FRestResponseState(const FRestResponseState&) = delete;
        FRestResponseState& operator=(const FRestResponseState&) = delete;

        bool Complete(int32 Code, const FString& Body);
        bool IsComplete() const;
        bool TryGetResponse(int32& OutCode, FString& OutBody) const;
    };
}
