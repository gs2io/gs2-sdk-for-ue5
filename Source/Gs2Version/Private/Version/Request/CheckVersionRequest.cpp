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

#include "Version/Request/CheckVersionRequest.h"

namespace Gs2::Version::Request
{
    FCheckVersionRequest::FCheckVersionRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TargetVersionsValue(nullptr)
    {
    }

    FCheckVersionRequest::FCheckVersionRequest(
        const FCheckVersionRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TargetVersionsValue(From.TargetVersionsValue)
    {
    }

    TSharedPtr<FCheckVersionRequest> FCheckVersionRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionRequest> FCheckVersionRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionRequest> FCheckVersionRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionRequest> FCheckVersionRequest::WithTargetVersions(
        const TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> TargetVersions
    )
    {
        this->TargetVersionsValue = TargetVersions;
        return SharedThis(this);
    }

    TSharedPtr<FCheckVersionRequest> FCheckVersionRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCheckVersionRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCheckVersionRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCheckVersionRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FTargetVersion>>> FCheckVersionRequest::GetTargetVersions() const
    {
        if (!TargetVersionsValue.IsValid())
        {
            return nullptr;
        }
        return TargetVersionsValue;
    }

    TOptional<FString> FCheckVersionRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCheckVersionRequest> FCheckVersionRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCheckVersionRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
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

    TSharedPtr<FJsonObject> FCheckVersionRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
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