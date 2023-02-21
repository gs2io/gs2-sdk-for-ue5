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

#include "Quest/Request/EndRequest.h"

namespace Gs2::Quest::Request
{
    FEndRequest::FEndRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        RewardsValue(nullptr),
        IsCompleteValue(TOptional<bool>()),
        ConfigValue(nullptr)
    {
    }

    FEndRequest::FEndRequest(
        const FEndRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TransactionIdValue(From.TransactionIdValue),
        RewardsValue(From.RewardsValue),
        IsCompleteValue(From.IsCompleteValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FEndRequest> FEndRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithIsComplete(
        const TOptional<bool> IsComplete
    )
    {
        this->IsCompleteValue = IsComplete;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FEndRequest> FEndRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FEndRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FEndRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FEndRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FEndRequest::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FReward>>> FEndRequest::GetRewards() const
    {
        if (!RewardsValue.IsValid())
        {
            return nullptr;
        }
        return RewardsValue;
    }

    TOptional<bool> FEndRequest::GetIsComplete() const
    {
        return IsCompleteValue;
    }

    FString FEndRequest::GetIsCompleteString() const
    {
        if (!IsCompleteValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsCompleteValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FEndRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FEndRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FEndRequest> FEndRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEndRequest>()
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
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("transactionId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithRewards(Data->HasField("rewards") ? [Data]() -> TSharedPtr<TArray<Model::FRewardPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRewardPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("rewards") && Data->HasTypedField<EJson::Array>("rewards"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("rewards"))
                      {
                          v->Add(Model::FReward::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithIsComplete(Data->HasField("isComplete") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("isComplete", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithConfig(Data->HasField("config") ? [Data]() -> TSharedPtr<TArray<Model::FConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("config") && Data->HasTypedField<EJson::Array>("config"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("config"))
                      {
                          v->Add(Model::FConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FEndRequest::ToJson() const
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
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (RewardsValue != nullptr && RewardsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RewardsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("rewards", v);
        }
        if (IsCompleteValue.IsSet())
        {
            JsonRootObject->SetBoolField("isComplete", IsCompleteValue.GetValue());
        }
        if (ConfigValue != nullptr && ConfigValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConfigValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("config", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}