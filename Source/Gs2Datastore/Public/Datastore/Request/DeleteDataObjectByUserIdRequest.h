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
    class FDeleteDataObjectByUserIdRequest;

    class GS2DATASTORE_API FDeleteDataObjectByUserIdRequest final : public TSharedFromThis<FDeleteDataObjectByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteDataObjectByUserIdRequest();
        FDeleteDataObjectByUserIdRequest(
            const FDeleteDataObjectByUserIdRequest& From
        );
        ~FDeleteDataObjectByUserIdRequest() = default;

        TSharedPtr<FDeleteDataObjectByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteDataObjectByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteDataObjectByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteDataObjectByUserIdRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FDeleteDataObjectByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteDataObjectByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteDataObjectByUserIdRequest, ESPMode::ThreadSafe> FDeleteDataObjectByUserIdRequestPtr;
}