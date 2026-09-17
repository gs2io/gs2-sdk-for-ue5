#pragma once

#include "CoreMinimal.h"
#include "HAL/CriticalSection.h"

namespace Gs2::Core::Net::Rest
{
    class GS2CORE_API FRestBinaryResponseState
    {
        mutable FCriticalSection Mutex;
        bool bCompleted = false;
        int32 ResponseCode = 999;
        TArray<uint8> ResponseBody;

    public:
        FRestBinaryResponseState() = default;
        FRestBinaryResponseState(const FRestBinaryResponseState&) = delete;
        FRestBinaryResponseState& operator=(const FRestBinaryResponseState&) = delete;

        bool Complete(int32 Code, const TArray<uint8>& Body);
        bool IsComplete() const;
        bool TryGetResponse(int32& OutCode, TArray<uint8>& OutBody) const;
    };
}
