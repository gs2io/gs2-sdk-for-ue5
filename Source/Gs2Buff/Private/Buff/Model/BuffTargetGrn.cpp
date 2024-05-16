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

#include "Buff/Model/BuffTargetGrn.h"

namespace Gs2::Buff::Model
{
    FBuffTargetGrn::FBuffTargetGrn():
        TargetModelNameValue(TOptional<FString>()),
        TargetGrnValue(TOptional<FString>())
    {
    }

    FBuffTargetGrn::FBuffTargetGrn(
        const FBuffTargetGrn& From
    ):
        TargetModelNameValue(From.TargetModelNameValue),
        TargetGrnValue(From.TargetGrnValue)
    {
    }

    TSharedPtr<FBuffTargetGrn> FBuffTargetGrn::WithTargetModelName(
        const TOptional<FString> TargetModelName
    )
    {
        this->TargetModelNameValue = TargetModelName;
        return SharedThis(this);
    }

    TSharedPtr<FBuffTargetGrn> FBuffTargetGrn::WithTargetGrn(
        const TOptional<FString> TargetGrn
    )
    {
        this->TargetGrnValue = TargetGrn;
        return SharedThis(this);
    }
    TOptional<FString> FBuffTargetGrn::GetTargetModelName() const
    {
        return TargetModelNameValue;
    }
    TOptional<FString> FBuffTargetGrn::GetTargetGrn() const
    {
        return TargetGrnValue;
    }

    TSharedPtr<FBuffTargetGrn> FBuffTargetGrn::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBuffTargetGrn>()
            ->WithTargetModelName(Data->HasField(ANSI_TO_TCHAR("targetModelName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetModelName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetGrn(Data->HasField(ANSI_TO_TCHAR("targetGrn")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetGrn"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FBuffTargetGrn::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TargetModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("targetModelName", TargetModelNameValue.GetValue());
        }
        if (TargetGrnValue.IsSet())
        {
            JsonRootObject->SetStringField("targetGrn", TargetGrnValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBuffTargetGrn::TypeName = "BuffTargetGrn";
}