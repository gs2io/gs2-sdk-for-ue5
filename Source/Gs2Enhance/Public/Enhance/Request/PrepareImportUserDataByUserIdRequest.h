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

namespace Gs2::Enhance::Request
{
    class FPrepareImportUserDataByUserIdRequest;

    class GS2ENHANCE_API FPrepareImportUserDataByUserIdRequest final : public TSharedFromThis<FPrepareImportUserDataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareImportUserDataByUserIdRequest();
        FPrepareImportUserDataByUserIdRequest(
            const FPrepareImportUserDataByUserIdRequest& From
        );
        ~FPrepareImportUserDataByUserIdRequest() = default;

        TSharedPtr<FPrepareImportUserDataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareImportUserDataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPrepareImportUserDataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPrepareImportUserDataByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareImportUserDataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareImportUserDataByUserIdRequest, ESPMode::ThreadSafe> FPrepareImportUserDataByUserIdRequestPtr;
}