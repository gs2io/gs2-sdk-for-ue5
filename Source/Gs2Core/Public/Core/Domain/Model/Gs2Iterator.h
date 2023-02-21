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

#pragma once

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "CoreMinimal.h"
#include "Core/Model/Gs2Error.h"

namespace Gs2::Core::Domain::Model
{
    template <class TResult, class TLoadTask>
    class TGs2Iterator:
        public TSharedFromThis<TGs2Iterator<TResult, TLoadTask>>
    {
    protected:
        TSharedPtr<TResult> Current;
        Gs2::Core::Model::FGs2ErrorPtr ErrorValue;
        
        virtual TSharedPtr<FAsyncTask<TLoadTask>> Load() = 0;

    public:
        TArray<TSharedPtr<TResult>> Result;
        bool Last;
        TGs2Iterator():
            Current(nullptr),
            ErrorValue(nullptr),
            Result(TArray<TSharedPtr<TResult>>()),
            Last(false)
        {
        }

        virtual ~TGs2Iterator() = default;

        Gs2::Core::Model::FGs2ErrorPtr Error() const
        {
            return ErrorValue;
        }
        
        bool IsError() const
        {
            return ErrorValue != nullptr;
        }
        
        class FNextTask final :
            public Gs2::Core::Util::TGs2Future<TResult>,
            public TSharedFromThis<FNextTask>
        {
            const TSharedPtr<TGs2Iterator<TResult, TLoadTask>> Self;
        public:
            explicit FNextTask(
                const TSharedPtr<TGs2Iterator<TResult, TLoadTask>> Self
            ): Self(Self)
            {
                
            }

            bool HasNext()
            {
                if (Self->ErrorValue != nullptr) return false;
                return Self->Result.Num() != 0 || !Self->Last;
            }

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TResult>> Result
            ) override
            {
                if (Self->Result.Num() == 0 && !Self->Last) {
                    const auto Future = Self->Load();
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        Self->ErrorValue = Future->GetTask().Error();
                        return Future->GetTask().Error();
                    }
                    if (Future->GetTask().Result().IsValid())
                    {
                        for (const auto Item : *Future->GetTask().Result())
                        {
                            Self->Result.Add(Item);
                        }
                    }
                    Future->EnsureCompletion();
                }
                if (Self->Result.Num() == 0) {
                    *Result = nullptr;
                    return nullptr;
                }
                const auto Ret = Self->Result[0];
                Self->Result.RemoveAt(0);
                *Result = Ret;
                if (Self->Result.Num() == 0 && !Self->Last) {
                    const auto Future = Self->Load();
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        return Future->GetTask().Error();
                    }
                    for (const auto Item : *Future->GetTask().Result())
                    {
                        Self->Result.Add(Item);
                    }
                    Future->EnsureCompletion();
                }
                return nullptr;
            }
        };
        friend FNextTask;

        virtual TSharedPtr<FAsyncTask<FNextTask>> Next()
        {
            return Gs2::Core::Util::New<FAsyncTask<FNextTask>>(this->AsShared());
        }
    };
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

