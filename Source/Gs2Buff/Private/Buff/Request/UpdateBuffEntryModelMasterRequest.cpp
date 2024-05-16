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

#include "Buff/Request/UpdateBuffEntryModelMasterRequest.h"

namespace Gs2::Buff::Request
{
    FUpdateBuffEntryModelMasterRequest::FUpdateBuffEntryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        BuffEntryNameValue(TOptional<FString>()),
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

    FUpdateBuffEntryModelMasterRequest::FUpdateBuffEntryModelMasterRequest(
        const FUpdateBuffEntryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BuffEntryNameValue(From.BuffEntryNameValue),
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

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithBuffEntryName(
        const TOptional<FString> BuffEntryName
    )
    {
        this->BuffEntryNameValue = BuffEntryName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithTargetType(
        const TOptional<FString> TargetType
    )
    {
        this->TargetTypeValue = TargetType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithTargetModel(
        const TSharedPtr<Model::FBuffTargetModel> TargetModel
    )
    {
        this->TargetModelValue = TargetModel;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithTargetAction(
        const TSharedPtr<Model::FBuffTargetAction> TargetAction
    )
    {
        this->TargetActionValue = TargetAction;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithExpression(
        const TOptional<FString> Expression
    )
    {
        this->ExpressionValue = Expression;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithPriority(
        const TOptional<int32> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::WithApplyPeriodScheduleEventId(
        const TOptional<FString> ApplyPeriodScheduleEventId
    )
    {
        this->ApplyPeriodScheduleEventIdValue = ApplyPeriodScheduleEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetBuffEntryName() const
    {
        return BuffEntryNameValue;
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetTargetType() const
    {
        return TargetTypeValue;
    }

    TSharedPtr<Model::FBuffTargetModel> FUpdateBuffEntryModelMasterRequest::GetTargetModel() const
    {
        if (!TargetModelValue.IsValid())
        {
            return nullptr;
        }
        return TargetModelValue;
    }

    TSharedPtr<Model::FBuffTargetAction> FUpdateBuffEntryModelMasterRequest::GetTargetAction() const
    {
        if (!TargetActionValue.IsValid())
        {
            return nullptr;
        }
        return TargetActionValue;
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetExpression() const
    {
        return ExpressionValue;
    }

    TOptional<int32> FUpdateBuffEntryModelMasterRequest::GetPriority() const
    {
        return PriorityValue;
    }

    FString FUpdateBuffEntryModelMasterRequest::GetPriorityString() const
    {
        if (!PriorityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PriorityValue.GetValue());
    }

    TOptional<FString> FUpdateBuffEntryModelMasterRequest::GetApplyPeriodScheduleEventId() const
    {
        return ApplyPeriodScheduleEventIdValue;
    }

    TSharedPtr<FUpdateBuffEntryModelMasterRequest> FUpdateBuffEntryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateBuffEntryModelMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBuffEntryName(Data->HasField(ANSI_TO_TCHAR("buffEntryName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("buffEntryName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetType(Data->HasField(ANSI_TO_TCHAR("targetType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTargetModel(Data->HasField(ANSI_TO_TCHAR("targetModel")) ? [Data]() -> Model::FBuffTargetModelPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetModel")))
                  {
                      return nullptr;
                  }
                  return Model::FBuffTargetModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetModel")));
              }() : nullptr)
          ->WithTargetAction(Data->HasField(ANSI_TO_TCHAR("targetAction")) ? [Data]() -> Model::FBuffTargetActionPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetAction")))
                  {
                      return nullptr;
                  }
                  return Model::FBuffTargetAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetAction")));
              }() : nullptr)
            ->WithExpression(Data->HasField(ANSI_TO_TCHAR("expression")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("expression"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPriority(Data->HasField(ANSI_TO_TCHAR("priority")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("priority"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithApplyPeriodScheduleEventId(Data->HasField(ANSI_TO_TCHAR("applyPeriodScheduleEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("applyPeriodScheduleEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateBuffEntryModelMasterRequest::ToJson() const
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
        if (BuffEntryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("buffEntryName", BuffEntryNameValue.GetValue());
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