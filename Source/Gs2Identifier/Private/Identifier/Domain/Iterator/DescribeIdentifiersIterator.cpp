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

#include "Identifier/Domain/Iterator/DescribeIdentifiersIterator.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/User.h"

namespace Gs2::Identifier::Domain::Iterator
{

    FDescribeIdentifiersIterator::FDescribeIdentifiersIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        UserName(UserName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeIdentifiersIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FIdentifier>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeIdentifiersIterator::FIterator::FIterator(
        const TSharedRef<FDescribeIdentifiersIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeIdentifiersIterator::FIterator& FDescribeIdentifiersIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
            Self->UserName,
            "Identifier"
        );
            if (Self->Cache->IsListCached(
                Gs2::Identifier::Model::FIdentifier::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Identifier::Model::FIdentifierPtr>>();
                *Range = Self->Cache->List<Gs2::Identifier::Model::FIdentifier>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeIdentifiers(
                MakeShared<Gs2::Identifier::Request::FDescribeIdentifiersRequest>()
                    ->WithUserName(Self->UserName)
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
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Identifier::Model::FIdentifier::TypeName,
                    ListParentKey,
                    Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                        Item->GetClientId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeIdentifiersIterator::FIterator FDescribeIdentifiersIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeIdentifiersIterator::FIterator FDescribeIdentifiersIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeIdentifiersIterator::FIterator FDescribeIdentifiersIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

