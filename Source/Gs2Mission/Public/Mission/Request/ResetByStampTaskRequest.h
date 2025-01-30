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

namespace Gs2::Mission::Request
{
    class FResetByStampTaskRequest;

    class GS2MISSION_API FResetByStampTaskRequest final : public TSharedFromThis<FResetByStampTaskRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampTaskValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FResetByStampTaskRequest();
        FResetByStampTaskRequest(
            const FResetByStampTaskRequest& From
        );
        ~FResetByStampTaskRequest() = default;

        TSharedPtr<FResetByStampTaskRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FResetByStampTaskRequest> WithStampTask(const TOptional<FString> StampTask);
        TSharedPtr<FResetByStampTaskRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampTask() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FResetByStampTaskRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FResetByStampTaskRequest> FResetByStampTaskRequestPtr;
}