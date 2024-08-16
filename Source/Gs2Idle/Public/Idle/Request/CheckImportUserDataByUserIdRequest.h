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

namespace Gs2::Idle::Request
{
    class FCheckImportUserDataByUserIdRequest;

    class GS2IDLE_API FCheckImportUserDataByUserIdRequest final : public TSharedFromThis<FCheckImportUserDataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> UploadTokenValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FCheckImportUserDataByUserIdRequest();
        FCheckImportUserDataByUserIdRequest(
            const FCheckImportUserDataByUserIdRequest& From
        );
        ~FCheckImportUserDataByUserIdRequest() = default;

        TSharedPtr<FCheckImportUserDataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCheckImportUserDataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCheckImportUserDataByUserIdRequest> WithUploadToken(const TOptional<FString> UploadToken);
        TSharedPtr<FCheckImportUserDataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetUploadToken() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FCheckImportUserDataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCheckImportUserDataByUserIdRequest> FCheckImportUserDataByUserIdRequestPtr;
}