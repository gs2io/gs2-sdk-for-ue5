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
    class FPrepareDownloadByUserIdRequest;

    class GS2DATASTORE_API FPrepareDownloadByUserIdRequest final : public TSharedFromThis<FPrepareDownloadByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DataObjectIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareDownloadByUserIdRequest();
        FPrepareDownloadByUserIdRequest(
            const FPrepareDownloadByUserIdRequest& From
        );
        ~FPrepareDownloadByUserIdRequest() = default;

        TSharedPtr<FPrepareDownloadByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareDownloadByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareDownloadByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPrepareDownloadByUserIdRequest> WithDataObjectId(const TOptional<FString> DataObjectId);
        TSharedPtr<FPrepareDownloadByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDataObjectId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareDownloadByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadByUserIdRequest, ESPMode::ThreadSafe> FPrepareDownloadByUserIdRequestPtr;
}