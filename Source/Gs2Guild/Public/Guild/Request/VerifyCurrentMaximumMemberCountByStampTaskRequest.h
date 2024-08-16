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
#include "Dom/JsonObject.h"

namespace Gs2::Guild::Request
{
    class FVerifyCurrentMaximumMemberCountByStampTaskRequest;

    class GS2GUILD_API FVerifyCurrentMaximumMemberCountByStampTaskRequest final : public TSharedFromThis<FVerifyCurrentMaximumMemberCountByStampTaskRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampTaskValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FVerifyCurrentMaximumMemberCountByStampTaskRequest();
        FVerifyCurrentMaximumMemberCountByStampTaskRequest(
            const FVerifyCurrentMaximumMemberCountByStampTaskRequest& From
        );
        ~FVerifyCurrentMaximumMemberCountByStampTaskRequest() = default;

        TSharedPtr<FVerifyCurrentMaximumMemberCountByStampTaskRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByStampTaskRequest> WithStampTask(const TOptional<FString> StampTask);
        TSharedPtr<FVerifyCurrentMaximumMemberCountByStampTaskRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampTask() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FVerifyCurrentMaximumMemberCountByStampTaskRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCurrentMaximumMemberCountByStampTaskRequest> FVerifyCurrentMaximumMemberCountByStampTaskRequestPtr;
}