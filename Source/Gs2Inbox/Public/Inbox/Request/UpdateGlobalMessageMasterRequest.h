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
#include "../Model/AcquireAction.h"
#include "../Model/TimeSpan.h"

namespace Gs2::Inbox::Request
{
    class FUpdateGlobalMessageMasterRequest;

    class GS2INBOX_API FUpdateGlobalMessageMasterRequest final : public TSharedFromThis<FUpdateGlobalMessageMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GlobalMessageNameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActionsValue;
        TSharedPtr<Model::FTimeSpan> ExpiresTimeSpanValue;
        TOptional<int64> ExpiresAtValue;
        
    public:
        
        FUpdateGlobalMessageMasterRequest();
        FUpdateGlobalMessageMasterRequest(
            const FUpdateGlobalMessageMasterRequest& From
        );
        ~FUpdateGlobalMessageMasterRequest() = default;

        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithGlobalMessageName(const TOptional<FString> GlobalMessageName);
        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithReadAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions);
        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithExpiresTimeSpan(const TSharedPtr<Model::FTimeSpan> ExpiresTimeSpan);
        TSharedPtr<FUpdateGlobalMessageMasterRequest> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGlobalMessageName() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetReadAcquireActions() const;
        TSharedPtr<Model::FTimeSpan> GetExpiresTimeSpan() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        static TSharedPtr<FUpdateGlobalMessageMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGlobalMessageMasterRequest, ESPMode::ThreadSafe> FUpdateGlobalMessageMasterRequestPtr;
}