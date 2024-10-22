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

#include "Distributor/Result/FreezeMasterDataResult.h"

namespace Gs2::Distributor::Result
{
    FFreezeMasterDataResult::FFreezeMasterDataResult():
        NewContextStackValue(TOptional<FString>())
    {
    }

    FFreezeMasterDataResult::FFreezeMasterDataResult(
        const FFreezeMasterDataResult& From
    ):
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FFreezeMasterDataResult> FFreezeMasterDataResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TOptional<FString> FFreezeMasterDataResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FFreezeMasterDataResult> FFreezeMasterDataResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFreezeMasterDataResult>()
            ->WithNewContextStack(Data->HasField(ANSI_TO_TCHAR("newContextStack")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("newContextStack"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FFreezeMasterDataResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NewContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("newContextStack", NewContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}