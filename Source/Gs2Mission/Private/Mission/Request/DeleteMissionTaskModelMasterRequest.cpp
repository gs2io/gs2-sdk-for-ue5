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

#include "Mission/Request/DeleteMissionTaskModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FDeleteMissionTaskModelMasterRequest::FDeleteMissionTaskModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>()),
        MissionTaskNameValue(TOptional<FString>())
    {
    }

    FDeleteMissionTaskModelMasterRequest::FDeleteMissionTaskModelMasterRequest(
        const FDeleteMissionTaskModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MissionGroupNameValue(From.MissionGroupNameValue),
        MissionTaskNameValue(From.MissionTaskNameValue)
    {
    }

    TSharedPtr<FDeleteMissionTaskModelMasterRequest> FDeleteMissionTaskModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteMissionTaskModelMasterRequest> FDeleteMissionTaskModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteMissionTaskModelMasterRequest> FDeleteMissionTaskModelMasterRequest::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteMissionTaskModelMasterRequest> FDeleteMissionTaskModelMasterRequest::WithMissionTaskName(
        const TOptional<FString> MissionTaskName
    )
    {
        this->MissionTaskNameValue = MissionTaskName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteMissionTaskModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteMissionTaskModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteMissionTaskModelMasterRequest::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }

    TOptional<FString> FDeleteMissionTaskModelMasterRequest::GetMissionTaskName() const
    {
        return MissionTaskNameValue;
    }

    TSharedPtr<FDeleteMissionTaskModelMasterRequest> FDeleteMissionTaskModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteMissionTaskModelMasterRequest>()
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
            ->WithMissionGroupName(Data->HasField("missionGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("missionGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMissionTaskName(Data->HasField("missionTaskName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("missionTaskName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteMissionTaskModelMasterRequest::ToJson() const
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
        if (MissionGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionGroupName", MissionGroupNameValue.GetValue());
        }
        if (MissionTaskNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionTaskName", MissionTaskNameValue.GetValue());
        }
        return JsonRootObject;
    }
}