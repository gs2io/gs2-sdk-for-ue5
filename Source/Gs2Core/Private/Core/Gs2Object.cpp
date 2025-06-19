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

#include "Core/Gs2Object.h"

TOptional<FString> FGs2Object::AsText(TSharedPtr<FJsonValue> Data)
{
    if (!Data || Data->IsNull())
    {
        return TOptional<FString>();
    }
    const auto V = Data->AsString();
    if (V.IsEmpty())
    {
        return TOptional<FString>();
    }
    return V;
}

TOptional<int32> FGs2Object::IntValue(TSharedPtr<FJsonValue> Data)
{
    if (!Data || Data->IsNull())
    {
        return TOptional<int32>();
    }
    return Data->AsNumber();
}

TOptional<int64> FGs2Object::LongValue(TSharedPtr<FJsonValue> Data)
{
    if (!Data || Data->IsNull())
    {
        return TOptional<int64>();
    }
    return Data->AsNumber();
}

TOptional<float> FGs2Object::FloatValue(TSharedPtr<FJsonValue> Data)
{
    if (!Data || Data->IsNull())
    {
        return TOptional<float>();
    }
    return Data->AsNumber();
}

TOptional<double> FGs2Object::DoubleValue(TSharedPtr<FJsonValue> Data)
{
    if (!Data || Data->IsNull())
    {
        return TOptional<double>();
    }
    return Data->AsNumber();
}

TOptional<bool> FGs2Object::BoolValue(TSharedPtr<FJsonValue> Data)
{
    if (!Data || Data->IsNull())
    {
        return TOptional<bool>();
    }
    return Data->AsBool();
}
