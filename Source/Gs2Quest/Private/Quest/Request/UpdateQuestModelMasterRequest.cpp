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

#include "Quest/Request/UpdateQuestModelMasterRequest.h"

namespace Gs2::Quest::Request
{
    FUpdateQuestModelMasterRequest::FUpdateQuestModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        QuestNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ContentsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        FirstCompleteAcquireActionsValue(nullptr),
        ConsumeActionsValue(nullptr),
        FailedAcquireActionsValue(nullptr),
        PremiseQuestNamesValue(nullptr)
    {
    }

    FUpdateQuestModelMasterRequest::FUpdateQuestModelMasterRequest(
        const FUpdateQuestModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        QuestNameValue(From.QuestNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ContentsValue(From.ContentsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        FirstCompleteAcquireActionsValue(From.FirstCompleteAcquireActionsValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        FailedAcquireActionsValue(From.FailedAcquireActionsValue),
        PremiseQuestNamesValue(From.PremiseQuestNamesValue)
    {
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithQuestName(
        const TOptional<FString> QuestName
    )
    {
        this->QuestNameValue = QuestName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithContents(
        const TSharedPtr<TArray<TSharedPtr<Model::FContents>>> Contents
    )
    {
        this->ContentsValue = Contents;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithFirstCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActions
    )
    {
        this->FirstCompleteAcquireActionsValue = FirstCompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithFailedAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActions
    )
    {
        this->FailedAcquireActionsValue = FailedAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::WithPremiseQuestNames(
        const TSharedPtr<TArray<FString>> PremiseQuestNames
    )
    {
        this->PremiseQuestNamesValue = PremiseQuestNames;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetQuestName() const
    {
        return QuestNameValue;
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FContents>>> FUpdateQuestModelMasterRequest::GetContents() const
    {
        if (!ContentsValue.IsValid())
        {
            return nullptr;
        }
        return ContentsValue;
    }

    TOptional<FString> FUpdateQuestModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FUpdateQuestModelMasterRequest::GetFirstCompleteAcquireActions() const
    {
        if (!FirstCompleteAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return FirstCompleteAcquireActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FUpdateQuestModelMasterRequest::GetConsumeActions() const
    {
        if (!ConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return ConsumeActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FUpdateQuestModelMasterRequest::GetFailedAcquireActions() const
    {
        if (!FailedAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return FailedAcquireActionsValue;
    }

    TSharedPtr<TArray<FString>> FUpdateQuestModelMasterRequest::GetPremiseQuestNames() const
    {
        if (!PremiseQuestNamesValue.IsValid())
        {
            return nullptr;
        }
        return PremiseQuestNamesValue;
    }

    TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateQuestModelMasterRequest>()
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
            ->WithQuestGroupName(Data->HasField("questGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("questGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithQuestName(Data->HasField("questName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("questName", v))
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
          ->WithContents(Data->HasField("contents") ? [Data]() -> TSharedPtr<TArray<Model::FContentsPtr>>
              {
                  auto v = MakeShared<TArray<Model::FContentsPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("contents") && Data->HasTypedField<EJson::Array>("contents"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("contents"))
                      {
                          v->Add(Model::FContents::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithChallengePeriodEventId(Data->HasField("challengePeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("challengePeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithFirstCompleteAcquireActions(Data->HasField("firstCompleteAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("firstCompleteAcquireActions") && Data->HasTypedField<EJson::Array>("firstCompleteAcquireActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("firstCompleteAcquireActions"))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithConsumeActions(Data->HasField("consumeActions") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("consumeActions") && Data->HasTypedField<EJson::Array>("consumeActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("consumeActions"))
                      {
                          v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithFailedAcquireActions(Data->HasField("failedAcquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("failedAcquireActions") && Data->HasTypedField<EJson::Array>("failedAcquireActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("failedAcquireActions"))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithPremiseQuestNames(Data->HasField("premiseQuestNames") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("premiseQuestNames") && Data->HasTypedField<EJson::Array>("premiseQuestNames"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("premiseQuestNames"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateQuestModelMasterRequest::ToJson() const
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
        if (QuestGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("questGroupName", QuestGroupNameValue.GetValue());
        }
        if (QuestNameValue.IsSet())
        {
            JsonRootObject->SetStringField("questName", QuestNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ContentsValue != nullptr && ContentsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ContentsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("contents", v);
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        if (FirstCompleteAcquireActionsValue != nullptr && FirstCompleteAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *FirstCompleteAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("firstCompleteAcquireActions", v);
        }
        if (ConsumeActionsValue != nullptr && ConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeActions", v);
        }
        if (FailedAcquireActionsValue != nullptr && FailedAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *FailedAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("failedAcquireActions", v);
        }
        if (PremiseQuestNamesValue != nullptr && PremiseQuestNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PremiseQuestNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("premiseQuestNames", v);
        }
        return JsonRootObject;
    }
}