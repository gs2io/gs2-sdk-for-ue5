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

#include "Distributor/Result/IfExpressionByUserIdResult.h"

namespace Gs2::Distributor::Result
{
    FIfExpressionByUserIdResult::FIfExpressionByUserIdResult():
        ItemValue(nullptr),
        ExpressionResultValue(TOptional<bool>())
    {
    }

    FIfExpressionByUserIdResult::FIfExpressionByUserIdResult(
        const FIfExpressionByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        ExpressionResultValue(From.ExpressionResultValue)
    {
    }

    TSharedPtr<FIfExpressionByUserIdResult> FIfExpressionByUserIdResult::WithItem(
        const TSharedPtr<Model::FTransactionResult> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FIfExpressionByUserIdResult> FIfExpressionByUserIdResult::WithExpressionResult(
        const TOptional<bool> ExpressionResult
    )
    {
        this->ExpressionResultValue = ExpressionResult;
        return SharedThis(this);
    }

    TSharedPtr<Model::FTransactionResult> FIfExpressionByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<bool> FIfExpressionByUserIdResult::GetExpressionResult() const
    {
        return ExpressionResultValue;
    }

    FString FIfExpressionByUserIdResult::GetExpressionResultString() const
    {
        if (!ExpressionResultValue.IsSet())
        {
            return FString("null");
        }
        return FString(ExpressionResultValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FIfExpressionByUserIdResult> FIfExpressionByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIfExpressionByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FTransactionResultPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionResult::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithExpressionResult(Data->HasField(ANSI_TO_TCHAR("expressionResult")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("expressionResult"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FIfExpressionByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ExpressionResultValue.IsSet())
        {
            JsonRootObject->SetBoolField("expressionResult", ExpressionResultValue.GetValue());
        }
        return JsonRootObject;
    }
}