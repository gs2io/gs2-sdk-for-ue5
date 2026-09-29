/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"

namespace Gs2::Core::Net::Rest
{
    enum class ERestTransportFailure : uint8
    {
        None,
        ConnectFailed,
        Timeout,
        Other,
    };

    class GS2CORE_API FRestSessionRequest final
    {
    public:
        FString Verb;
        FString Url;
        TArray<TPair<FString, FString>> Headers;
        TOptional<FString> Body;

        FRestSessionRequest() = default;
        FRestSessionRequest(
            const FString& Verb,
            const FString& Url
        );

        FRestSessionRequest& AddHeader(const FString& Name, const FString& Value);
        FRestSessionRequest& SetBody(const FString& InBody);

        bool IsIdempotent() const;
    };

    class GS2CORE_API FRestSessionResponse final
    {
    public:
        FString Url;
        int32 ResponseCode = 999;
        FString ResponseBody;
        ERestTransportFailure TransportFailure = ERestTransportFailure::Other;
        bool bRetried = false;

        bool HasResponse() const
        {
            return TransportFailure == ERestTransportFailure::None;
        }
    };
}
