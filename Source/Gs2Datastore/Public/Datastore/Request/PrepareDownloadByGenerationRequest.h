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
    class FPrepareDownloadByGenerationRequest;

    class GS2DATASTORE_API FPrepareDownloadByGenerationRequest final : public TSharedFromThis<FPrepareDownloadByGenerationRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DataObjectIdValue;
        TOptional<FString> GenerationValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareDownloadByGenerationRequest();
        FPrepareDownloadByGenerationRequest(
            const FPrepareDownloadByGenerationRequest& From
        );
        ~FPrepareDownloadByGenerationRequest() = default;

        TSharedPtr<FPrepareDownloadByGenerationRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareDownloadByGenerationRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareDownloadByGenerationRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPrepareDownloadByGenerationRequest> WithDataObjectId(const TOptional<FString> DataObjectId);
        TSharedPtr<FPrepareDownloadByGenerationRequest> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FPrepareDownloadByGenerationRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDataObjectId() const;
        TOptional<FString> GetGeneration() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareDownloadByGenerationRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadByGenerationRequest> FPrepareDownloadByGenerationRequestPtr;
}