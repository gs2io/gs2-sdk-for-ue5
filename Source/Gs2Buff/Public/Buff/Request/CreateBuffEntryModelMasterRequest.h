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
#include "../Model/BuffTargetModel.h"
#include "../Model/BuffTargetAction.h"

namespace Gs2::Buff::Request
{
    class FCreateBuffEntryModelMasterRequest;

    class GS2BUFF_API FCreateBuffEntryModelMasterRequest final : public TSharedFromThis<FCreateBuffEntryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExpressionValue;
        TOptional<FString> TargetTypeValue;
        TSharedPtr<Model::FBuffTargetModel> TargetModelValue;
        TSharedPtr<Model::FBuffTargetAction> TargetActionValue;
        TOptional<int32> PriorityValue;
        TOptional<FString> ApplyPeriodScheduleEventIdValue;
        
    public:
        
        FCreateBuffEntryModelMasterRequest();
        FCreateBuffEntryModelMasterRequest(
            const FCreateBuffEntryModelMasterRequest& From
        );
        ~FCreateBuffEntryModelMasterRequest() = default;

        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithExpression(const TOptional<FString> Expression);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithTargetType(const TOptional<FString> TargetType);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithTargetModel(const TSharedPtr<Model::FBuffTargetModel> TargetModel);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithTargetAction(const TSharedPtr<Model::FBuffTargetAction> TargetAction);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithPriority(const TOptional<int32> Priority);
        TSharedPtr<FCreateBuffEntryModelMasterRequest> WithApplyPeriodScheduleEventId(const TOptional<FString> ApplyPeriodScheduleEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetExpression() const;
        TOptional<FString> GetTargetType() const;
        TSharedPtr<Model::FBuffTargetModel> GetTargetModel() const;
        TSharedPtr<Model::FBuffTargetAction> GetTargetAction() const;
        TOptional<int32> GetPriority() const;
        FString GetPriorityString() const;
        TOptional<FString> GetApplyPeriodScheduleEventId() const;

        static TSharedPtr<FCreateBuffEntryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequestPtr;
}