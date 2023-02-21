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
    class FPrepareDownloadRequest;

    class GS2DATASTORE_API FPrepareDownloadRequest final : public TSharedFromThis<FPrepareDownloadRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DataObjectIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareDownloadRequest();
        FPrepareDownloadRequest(
            const FPrepareDownloadRequest& From
        );
        ~FPrepareDownloadRequest() = default;

        TSharedPtr<FPrepareDownloadRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareDownloadRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareDownloadRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPrepareDownloadRequest> WithDataObjectId(const TOptional<FString> DataObjectId);
        TSharedPtr<FPrepareDownloadRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDataObjectId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareDownloadRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadRequest, ESPMode::ThreadSafe> FPrepareDownloadRequestPtr;
}