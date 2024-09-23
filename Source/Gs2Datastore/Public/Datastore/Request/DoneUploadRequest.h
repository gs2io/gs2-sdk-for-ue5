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
    class FDoneUploadRequest;

    class GS2DATASTORE_API FDoneUploadRequest final : public TSharedFromThis<FDoneUploadRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDoneUploadRequest();
        FDoneUploadRequest(
            const FDoneUploadRequest& From
        );
        ~FDoneUploadRequest() = default;

        TSharedPtr<FDoneUploadRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoneUploadRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoneUploadRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FDoneUploadRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDoneUploadRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDoneUploadRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoneUploadRequest, ESPMode::ThreadSafe> FDoneUploadRequestPtr;
}