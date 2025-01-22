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

namespace Gs2::Gateway::Result
{
    class GS2GATEWAY_API FSendNotificationResult final : public TSharedFromThis<FSendNotificationResult>
    {
        TOptional<FString> ProtocolValue;
        TSharedPtr<TArray<FString>> SendConnectionIdsValue;
        
    public:
        
        FSendNotificationResult();
        FSendNotificationResult(
            const FSendNotificationResult& From
        );
        ~FSendNotificationResult() = default;

        TSharedPtr<FSendNotificationResult> WithProtocol(const TOptional<FString> Protocol);
        TSharedPtr<FSendNotificationResult> WithSendConnectionIds(const TSharedPtr<TArray<FString>> SendConnectionIds);

        TOptional<FString> GetProtocol() const;
        TSharedPtr<TArray<FString>> GetSendConnectionIds() const;

        static TSharedPtr<FSendNotificationResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendNotificationResult, ESPMode::ThreadSafe> FSendNotificationResultPtr;
}