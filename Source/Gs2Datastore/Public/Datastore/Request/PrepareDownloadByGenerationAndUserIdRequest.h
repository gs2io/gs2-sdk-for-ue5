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

namespace Gs2::Datastore::Request
{
    class FPrepareDownloadByGenerationAndUserIdRequest;

    class GS2DATASTORE_API FPrepareDownloadByGenerationAndUserIdRequest final : public TSharedFromThis<FPrepareDownloadByGenerationAndUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DataObjectIdValue;
        TOptional<FString> GenerationValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareDownloadByGenerationAndUserIdRequest();
        FPrepareDownloadByGenerationAndUserIdRequest(
            const FPrepareDownloadByGenerationAndUserIdRequest& From
        );
        ~FPrepareDownloadByGenerationAndUserIdRequest() = default;

        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithDataObjectId(const TOptional<FString> DataObjectId);
        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDataObjectId() const;
        TOptional<FString> GetGeneration() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadByGenerationAndUserIdRequest> FPrepareDownloadByGenerationAndUserIdRequestPtr;
}