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

namespace Gs2::Datastore::Request
{
    class FPrepareDownloadOwnDataByGenerationRequest;

    class GS2DATASTORE_API FPrepareDownloadOwnDataByGenerationRequest final : public TSharedFromThis<FPrepareDownloadOwnDataByGenerationRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> GenerationValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareDownloadOwnDataByGenerationRequest();
        FPrepareDownloadOwnDataByGenerationRequest(
            const FPrepareDownloadOwnDataByGenerationRequest& From
        );
        ~FPrepareDownloadOwnDataByGenerationRequest() = default;

        TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> WithGeneration(const TOptional<FString> Generation);
        TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetGeneration() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadOwnDataByGenerationRequest, ESPMode::ThreadSafe> FPrepareDownloadOwnDataByGenerationRequestPtr;
}