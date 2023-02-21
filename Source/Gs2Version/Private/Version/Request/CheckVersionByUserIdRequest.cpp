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

#include "Version/Request/CheckVersionByUserIdRequest.h"

namespace Gs2::Version::Request
{
    FCheckVersionByUserIdRequest::FCheckVersionByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TargetVersionsValue(nullptr)
    {
    }

    FCheckVersionByUserIdRequest::FCheckVersionByUserIdRequest(
        const FCheckVersionByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        TargetVersionsValue(From.TargetVersionsValue)
    {
    }

    TSharedPtr<FCheckVersionByUserIdRequest> FCheckVersionByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionByUserIdRequest> FCheckVersionByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionByUserIdRequest> FCheckVersionByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionByUserIdRequest> FCheckVersionByUserIdRequest::WithTargetVersions(
        const TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> TargetVersions
    )
    {
        this->TargetVersionsValue = TargetVersions;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionByUserIdRequest> FCheckVersionByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCheckVersionByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCheckVersionByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCheckVersionByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> FCheckVersionByUserIdRequest::GetTargetVersions() const
    {
        if (!TargetVersionsValue.IsValid())
        {
            return nullptr;
        }
        return TargetVersionsValue;
    }

    TOptional<FString> FCheckVersionByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCheckVersionByUserIdRequest> FCheckVersionByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCheckVersionByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTargetVersions(Data->HasField("targetVersions") ? [Data]() -> TSharedPtr<TArray<Model::FTargetVersionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FTargetVersionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("targetVersions") && Data->HasTypedField<EJson::Array>("targetVersions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("targetVersions"))
                      {
                          v->Add(Model::FTargetVersion::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCheckVersionByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TargetVersionsValue != nullptr && TargetVersionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TargetVersionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("targetVersions", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}