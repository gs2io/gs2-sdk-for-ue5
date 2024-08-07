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

#include "Quest/Request/CreateQuestModelMasterRequest.h"

namespace Gs2::Quest::Request
{
    FCreateQuestModelMasterRequest::FCreateQuestModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ContentsValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>()),
        FirstCompleteAcquireActionsValue(nullptr),
        VerifyActionsValue(nullptr),
        ConsumeActionsValue(nullptr),
        FailedAcquireActionsValue(nullptr),
        PremiseQuestNamesValue(nullptr)
    {
    }

    FCreateQuestModelMasterRequest::FCreateQuestModelMasterRequest(
        const FCreateQuestModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ContentsValue(From.ContentsValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue),
        FirstCompleteAcquireActionsValue(From.FirstCompleteAcquireActionsValue),
        VerifyActionsValue(From.VerifyActionsValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        FailedAcquireActionsValue(From.FailedAcquireActionsValue),
        PremiseQuestNamesValue(From.PremiseQuestNamesValue)
    {
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithContents(
        const TSharedPtr<TArray<TSharedPtr<Model::FContents>>> Contents
    )
    {
        this->ContentsValue = Contents;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithFirstCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActions
    )
    {
        this->FirstCompleteAcquireActionsValue = FirstCompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions
    )
    {
        this->VerifyActionsValue = VerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithFailedAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActions
    )
    {
        this->FailedAcquireActionsValue = FailedAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::WithPremiseQuestNames(
        const TSharedPtr<TArray<FString>> PremiseQuestNames
    )
    {
        this->PremiseQuestNamesValue = PremiseQuestNames;
        return SharedThis(this);
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FContents>>> FCreateQuestModelMasterRequest::GetContents() const
    {
        if (!ContentsValue.IsValid())
        {
            return nullptr;
        }
        return ContentsValue;
    }

    TOptional<FString> FCreateQuestModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FCreateQuestModelMasterRequest::GetFirstCompleteAcquireActions() const
    {
        if (!FirstCompleteAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return FirstCompleteAcquireActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FCreateQuestModelMasterRequest::GetVerifyActions() const
    {
        if (!VerifyActionsValue.IsValid())
        {
            return nullptr;
        }
        return VerifyActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FCreateQuestModelMasterRequest::GetConsumeActions() const
    {
        if (!ConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return ConsumeActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FCreateQuestModelMasterRequest::GetFailedAcquireActions() const
    {
        if (!FailedAcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return FailedAcquireActionsValue;
    }

    TSharedPtr<TArray<FString>> FCreateQuestModelMasterRequest::GetPremiseQuestNames() const
    {
        if (!PremiseQuestNamesValue.IsValid())
        {
            return nullptr;
        }
        return PremiseQuestNamesValue;
    }

    TSharedPtr<FCreateQuestModelMasterRequest> FCreateQuestModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateQuestModelMasterRequest>()
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
            ->WithQuestGroupName(Data->HasField(ANSI_TO_TCHAR("questGroupName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("questGroupName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
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
          ->WithContents(Data->HasField(ANSI_TO_TCHAR("contents")) ? [Data]() -> TSharedPtr<TArray<Model::FContentsPtr>>
              {
                  auto v = MakeShared<TArray<Model::FContentsPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("contents")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("contents")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("contents")))
                      {
                          v->Add(Model::FContents::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FContentsPtr>>())
            ->WithChallengePeriodEventId(Data->HasField(ANSI_TO_TCHAR("challengePeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("challengePeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithFirstCompleteAcquireActions(Data->HasField(ANSI_TO_TCHAR("firstCompleteAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("firstCompleteAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("firstCompleteAcquireActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("firstCompleteAcquireActions")))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
          ->WithVerifyActions(Data->HasField(ANSI_TO_TCHAR("verifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyActions")))
                      {
                          v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
          ->WithConsumeActions(Data->HasField(ANSI_TO_TCHAR("consumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("consumeActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("consumeActions")))
                      {
                          v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
          ->WithFailedAcquireActions(Data->HasField(ANSI_TO_TCHAR("failedAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("failedAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("failedAcquireActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("failedAcquireActions")))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
          ->WithPremiseQuestNames(Data->HasField(ANSI_TO_TCHAR("premiseQuestNames")) ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("premiseQuestNames")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("premiseQuestNames")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("premiseQuestNames")))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FCreateQuestModelMasterRequest::ToJson() const
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
        if (VerifyActionsValue != nullptr && VerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyActions", v);
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