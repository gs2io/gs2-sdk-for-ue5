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
    class FPrepareReUploadRequest;

    class GS2DATASTORE_API FPrepareReUploadRequest final : public TSharedFromThis<FPrepareReUploadRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ContentTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareReUploadRequest();
        FPrepareReUploadRequest(
            const FPrepareReUploadRequest& From
        );
        ~FPrepareReUploadRequest() = default;

        TSharedPtr<FPrepareReUploadRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareReUploadRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareReUploadRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FPrepareReUploadRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPrepareReUploadRequest> WithContentType(const TOptional<FString> ContentType);
        TSharedPtr<FPrepareReUploadRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetContentType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareReUploadRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequestPtr;
}