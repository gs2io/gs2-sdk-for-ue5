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

#include "Quest/Request/GetQuestModelMasterRequest.h"

namespace Gs2::Quest::Request
{
    FGetQuestModelMasterRequest::FGetQuestModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        QuestNameValue(TOptional<FString>())
    {
    }

    FGetQuestModelMasterRequest::FGetQuestModelMasterRequest(
        const FGetQuestModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        QuestNameValue(From.QuestNameValue)
    {
    }

    TSharedPtr<FGetQuestModelMasterRequest> FGetQuestModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetQuestModelMasterRequest> FGetQuestModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetQuestModelMasterRequest> FGetQuestModelMasterRequest::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FGetQuestModelMasterRequest> FGetQuestModelMasterRequest::WithQuestName(
        const TOptional<FString> QuestName
    )
    {
        this->QuestNameValue = QuestName;
        return SharedThis(this);
    }

    TOptional<FString> FGetQuestModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetQuestModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetQuestModelMasterRequest::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }

    TOptional<FString> FGetQuestModelMasterRequest::GetQuestName() const
    {
        return QuestNameValue;
    }

    TSharedPtr<FGetQuestModelMasterRequest> FGetQuestModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetQuestModelMasterRequest>()
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
            ->WithQuestName(Data->HasField("questName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("questName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetQuestModelMasterRequest::ToJson() const
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
        return JsonRootObject;
    }
}