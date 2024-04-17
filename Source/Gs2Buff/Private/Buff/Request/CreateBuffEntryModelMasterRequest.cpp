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

#include "Buff/Request/CreateBuffEntryModelMasterRequest.h"

namespace Gs2::Buff::Request
{
    FCreateBuffEntryModelMasterRequest::FCreateBuffEntryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TargetTypeValue(TOptional<FString>()),
        TargetModelValue(nullptr),
        TargetActionValue(nullptr),
        ExpressionValue(TOptional<FString>()),
        PriorityValue(TOptional<int32>()),
        ApplyPeriodScheduleEventIdValue(TOptional<FString>())
    {
    }

    FCreateBuffEntryModelMasterRequest::FCreateBuffEntryModelMasterRequest(
        const FCreateBuffEntryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TargetTypeValue(From.TargetTypeValue),
        TargetModelValue(From.TargetModelValue),
        TargetActionValue(From.TargetActionValue),
        ExpressionValue(From.ExpressionValue),
        PriorityValue(From.PriorityValue),
        ApplyPeriodScheduleEventIdValue(From.ApplyPeriodScheduleEventIdValue)
    {
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithTargetType(
        const TOptional<FString> TargetType
    )
    {
        this->TargetTypeValue = TargetType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithTargetModel(
        const TSharedPtr<Model::FBuffTargetModel> TargetModel
    )
    {
        this->TargetModelValue = TargetModel;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithTargetAction(
        const TSharedPtr<Model::FBuffTargetAction> TargetAction
    )
    {
        this->TargetActionValue = TargetAction;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithExpression(
        const TOptional<FString> Expression
    )
    {
        this->ExpressionValue = Expression;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithPriority(
        const TOptional<int32> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::WithApplyPeriodScheduleEventId(
        const TOptional<FString> ApplyPeriodScheduleEventId
    )
    {
        this->ApplyPeriodScheduleEventIdValue = ApplyPeriodScheduleEventId;
        return SharedThis(this);
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetTargetType() const
    {
        return TargetTypeValue;
    }

    TSharedPtr<Model::FBuffTargetModel> FCreateBuffEntryModelMasterRequest::GetTargetModel() const
    {
        if (!TargetModelValue.IsValid())
        {
            return nullptr;
        }
        return TargetModelValue;
    }

    TSharedPtr<Model::FBuffTargetAction> FCreateBuffEntryModelMasterRequest::GetTargetAction() const
    {
        if (!TargetActionValue.IsValid())
        {
            return nullptr;
        }
        return TargetActionValue;
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetExpression() const
    {
        return ExpressionValue;
    }

    TOptional<int32> FCreateBuffEntryModelMasterRequest::GetPriority() const
    {
        return PriorityValue;
    }

    FString FCreateBuffEntryModelMasterRequest::GetPriorityString() const
    {
        if (!PriorityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PriorityValue.GetValue());
    }

    TOptional<FString> FCreateBuffEntryModelMasterRequest::GetApplyPeriodScheduleEventId() const
    {
        return ApplyPeriodScheduleEventIdValue;
    }

    TSharedPtr<FCreateBuffEntryModelMasterRequest> FCreateBuffEntryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateBuffEntryModelMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetType(Data->HasField("targetType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("targetType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTargetModel(Data->HasField("targetModel") ? [Data]() -> Model::FBuffTargetModelPtr
              {
                  if (Data->HasTypedField<EJson::Null>("targetModel"))
                  {
                      return nullptr;
                  }
                  return Model::FBuffTargetModel::FromJson(Data->GetObjectField("targetModel"));
              }() : nullptr)
          ->WithTargetAction(Data->HasField("targetAction") ? [Data]() -> Model::FBuffTargetActionPtr
              {
                  if (Data->HasTypedField<EJson::Null>("targetAction"))
                  {
                      return nullptr;
                  }
                  return Model::FBuffTargetAction::FromJson(Data->GetObjectField("targetAction"));
              }() : nullptr)
            ->WithExpression(Data->HasField("expression") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("expression", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPriority(Data->HasField("priority") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("priority", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithApplyPeriodScheduleEventId(Data->HasField("applyPeriodScheduleEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("applyPeriodScheduleEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateBuffEntryModelMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (TargetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("targetType", TargetTypeValue.GetValue());
        }
        if (TargetModelValue != nullptr && TargetModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("targetModel", TargetModelValue->ToJson());
        }
        if (TargetActionValue != nullptr && TargetActionValue.IsValid())
        {
            JsonRootObject->SetObjectField("targetAction", TargetActionValue->ToJson());
        }
        if (ExpressionValue.IsSet())
        {
            JsonRootObject->SetStringField("expression", ExpressionValue.GetValue());
        }
        if (PriorityValue.IsSet())
        {
            JsonRootObject->SetNumberField("priority", PriorityValue.GetValue());
        }
        if (ApplyPeriodScheduleEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("applyPeriodScheduleEventId", ApplyPeriodScheduleEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}