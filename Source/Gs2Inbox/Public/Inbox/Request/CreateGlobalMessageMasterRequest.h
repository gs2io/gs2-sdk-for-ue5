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
#include "../Model/AcquireAction.h"
#include "../Model/TimeSpan.h"

namespace Gs2::Inbox::Request
{
    class FCreateGlobalMessageMasterRequest;

    class GS2INBOX_API FCreateGlobalMessageMasterRequest final : public TSharedFromThis<FCreateGlobalMessageMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActionsValue;
        TSharedPtr<Model::FTimeSpan> ExpiresTimeSpanValue;
        TOptional<int64> ExpiresAtValue;
        TOptional<FString> MessageReceptionPeriodEventIdValue;
        
    public:
        
        FCreateGlobalMessageMasterRequest();
        FCreateGlobalMessageMasterRequest(
            const FCreateGlobalMessageMasterRequest& From
        );
        ~FCreateGlobalMessageMasterRequest() = default;

        TSharedPtr<FCreateGlobalMessageMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithReadAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReadAcquireActions);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithExpiresTimeSpan(const TSharedPtr<Model::FTimeSpan> ExpiresTimeSpan);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FCreateGlobalMessageMasterRequest> WithMessageReceptionPeriodEventId(const TOptional<FString> MessageReceptionPeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetReadAcquireActions() const;
        TSharedPtr<Model::FTimeSpan> GetExpiresTimeSpan() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TOptional<FString> GetMessageReceptionPeriodEventId() const;

        static TSharedPtr<FCreateGlobalMessageMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGlobalMessageMasterRequest> FCreateGlobalMessageMasterRequestPtr;
}