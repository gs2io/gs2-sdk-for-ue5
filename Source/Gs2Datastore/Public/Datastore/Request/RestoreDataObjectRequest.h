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
    class FRestoreDataObjectRequest;

    class GS2DATASTORE_API FRestoreDataObjectRequest final : public TSharedFromThis<FRestoreDataObjectRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DataObjectIdValue;
        
    public:
        
        FRestoreDataObjectRequest();
        FRestoreDataObjectRequest(
            const FRestoreDataObjectRequest& From
        );
        ~FRestoreDataObjectRequest() = default;

        TSharedPtr<FRestoreDataObjectRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRestoreDataObjectRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRestoreDataObjectRequest> WithDataObjectId(const TOptional<FString> DataObjectId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDataObjectId() const;

        static TSharedPtr<FRestoreDataObjectRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRestoreDataObjectRequest, ESPMode::ThreadSafe> FRestoreDataObjectRequestPtr;
}