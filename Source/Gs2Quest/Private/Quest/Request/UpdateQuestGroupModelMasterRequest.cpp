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

#include "Quest/Request/UpdateQuestGroupModelMasterRequest.h"

namespace Gs2::Quest::Request
{
    FUpdateQuestGroupModelMasterRequest::FUpdateQuestGroupModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ChallengePeriodEventIdValue(TOptional<FString>())
    {
    }

    FUpdateQuestGroupModelMasterRequest::FUpdateQuestGroupModelMasterRequest(
        const FUpdateQuestGroupModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue)
    {
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateQuestGroupModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateQuestGroupModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateQuestGroupModelMasterRequest::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }

    TOptional<FString> FUpdateQuestGroupModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateQuestGroupModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateQuestGroupModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TSharedPtr<FUpdateQuestGroupModelMasterRequest> FUpdateQuestGroupModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateQuestGroupModelMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithQuestGroupName(Data->HasField("questGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("questGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithChallengePeriodEventId(Data->HasField("challengePeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("challengePeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateQuestGroupModelMasterRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}