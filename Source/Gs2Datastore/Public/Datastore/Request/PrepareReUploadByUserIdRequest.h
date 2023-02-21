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
    class FPrepareReUploadByUserIdRequest;

    class GS2DATASTORE_API FPrepareReUploadByUserIdRequest final : public TSharedFromThis<FPrepareReUploadByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ContentTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareReUploadByUserIdRequest();
        FPrepareReUploadByUserIdRequest(
            const FPrepareReUploadByUserIdRequest& From
        );
        ~FPrepareReUploadByUserIdRequest() = default;

        TSharedPtr<FPrepareReUploadByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareReUploadByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareReUploadByUserIdRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FPrepareReUploadByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPrepareReUploadByUserIdRequest> WithContentType(const TOptional<FString> ContentType);
        TSharedPtr<FPrepareReUploadByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetContentType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareReUploadByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareReUploadByUserIdRequest, ESPMode::ThreadSafe> FPrepareReUploadByUserIdRequestPtr;
}