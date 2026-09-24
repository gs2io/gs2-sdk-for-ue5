
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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Distributor/Domain/Iterator/DescribeUserDataIterator.h"
#include "Distributor/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Distributor::Domain::Iterator
{

    FDescribeUserDataIterator::FDescribeUserDataIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        AccessToken(AccessToken)
    {
    }

    FDescribeUserDataIterator::FDescribeUserDataIterator(
        const FDescribeUserDataIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        AccessToken(From.AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeUserDataIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FUserDataEntry>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeUserDataIterator::FIterator::FIterator(
        const TSharedRef<FDescribeUserDataIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeUserDataIterator::FIterator& FDescribeUserDataIterator::FIterator::operator++()
    {


        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto Future = Self->Client->DescribeUserData(
                MakeShared<Gs2::Distributor::Request::FDescribeUserDataRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Distributor::Model::FUserDataEntryPtr>>();
            for (const auto& Entry : *Range)
            {
                if (!Entry.IsValid()) continue;
                // 1 件の JSON が読めなくても（未設定が返る）他のエントリは入れる（個別 API で取り直せる）
                const auto ParentKey = Self->Gs2->Distributor->PutUserData(
                    Entry->GetService().Get(FString()),
                    Entry->GetNamespaceName(),
                    Self->UserId(),
                    Self->AccessToken->GetTimeOffset(),
                    Entry->GetKind().Get(FString()),
                    Entry->GetPayload().Get(FString())
                );
                if (!ParentKey.IsSet()) continue;
                const auto ListCachedKey = Entry->GetService().Get(FString()) + TEXT("\t") + Entry->GetKind().Get(FString()) + TEXT("\t") + *ParentKey;
                if (!Self->ListCachedKeys.Contains(ListCachedKey))
                {
                    Self->ListCachedKeys.Add(ListCachedKey);
                    Self->ListCached.Add(MakeTuple(Entry->GetService().Get(FString()), Entry->GetKind().Get(FString()), *ParentKey));
                }
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast)
            {
                for (const auto& Item : Self->ListCached)
                {
                    Self->Gs2->Distributor->SetListCached(Item.Get<0>(), Self->AccessToken->GetTimeOffset(), Item.Get<1>(), Item.Get<2>());
                }
                Self->ListCached.Reset();
                Self->ListCachedKeys.Reset();
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeUserDataIterator::FIterator FDescribeUserDataIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeUserDataIterator::FIterator FDescribeUserDataIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeUserDataIterator::FIterator FDescribeUserDataIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

