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

namespace Gs2::Guild::Request
{
    class FImportUserDataByUserIdRequest;

    class GS2GUILD_API FImportUserDataByUserIdRequest final : public TSharedFromThis<FImportUserDataByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> UploadTokenValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FImportUserDataByUserIdRequest();
        FImportUserDataByUserIdRequest(
            const FImportUserDataByUserIdRequest& From
        );
        ~FImportUserDataByUserIdRequest() = default;

        TSharedPtr<FImportUserDataByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FImportUserDataByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FImportUserDataByUserIdRequest> WithUploadToken(const TOptional<FString> UploadToken);
        TSharedPtr<FImportUserDataByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetUploadToken() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FImportUserDataByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FImportUserDataByUserIdRequest, ESPMode::ThreadSafe> FImportUserDataByUserIdRequestPtr;
}