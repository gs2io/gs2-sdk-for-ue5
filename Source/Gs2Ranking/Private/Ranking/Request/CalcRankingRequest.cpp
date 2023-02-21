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

#include "Ranking/Request/CalcRankingRequest.h"

namespace Gs2::Ranking::Request
{
    FCalcRankingRequest::FCalcRankingRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>())
    {
    }

    FCalcRankingRequest::FCalcRankingRequest(
        const FCalcRankingRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue)
    {
    }

    TSharedPtr<FCalcRankingRequest> FCalcRankingRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCalcRankingRequest> FCalcRankingRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCalcRankingRequest> FCalcRankingRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TOptional<FString> FCalcRankingRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCalcRankingRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCalcRankingRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TSharedPtr<FCalcRankingRequest> FCalcRankingRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCalcRankingRequest>()
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
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("categoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCalcRankingRequest::ToJson() const
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
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        return JsonRootObject;
    }
}